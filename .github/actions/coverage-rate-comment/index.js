const github = require('@actions/github');
const postPRInfo = require('./postPRInfo');

async function run() {
    try {
        const context = github.context;

        const response = await postPRInfo(
            context.repo.owner,
            context.repo.repo,
            context.payload.pull_request.number,
            context.runId
        );
    } catch (error) {
        core.setFailed(error.message);
    }
}

run();
